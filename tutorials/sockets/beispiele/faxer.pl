#!/usr/bin/perl
use strict;

# Dieses Programm bearbeitet automatisch eingehende E-Mails.
# Der Text des Body wird in einer Datei gespeichert.
# Um das Programm einzusetzen kann die Datei /etc/aliases auf dem
# Mailserver geaendert werden. Fuegen Sie die folgende Zeile ein:
#
# fax: "| /path/to/faxer.pl
#
# Vergessen Sie anschliessend den Aufruf von "newaliases" nicht!
#
# Folgende Variablen muessen vor Inbetriebnahme konfiguriert werden:
# ---------------------------------------------------------------------
# Pfad zum sendmail-Programm
my $MailProgram = '/usr/lib/sendmail -t';

# Pfad zum a2ps-Programm incl. der festen Parameter
my $a2psProgram = '/usr/bin/a2ps -nb -B -f -i -nP -q -s1 -nu -nv';
$a2psProgram = $a2psProgram . 'Xa4 -8 -1 -F10 -nL -p -ns';

# Wird Hylafax ($HYLA=1) oder Mgetty/Sendfax ($HYLA=0) verwendet
my $HYLA = 1;

# Pfad zum sendfax-Programm
my $Sendfax = '/usr/local/sendfax';

# Pfad zum Ghostscript-Programm (nur noetig beim Mgetty/Sendfax)
# inklusive feste Parameter
my $Ghost = '/usr/bin/gs -sDEVICE=dfaxhigh -dNOPAUSE ';

# ---------------------------------------------------------------------
############## AB HIER MUSS NICHTS MEHR GEAENDERT WERDEN ##############

my @IncomingHeader = ();            # Header der emfangenen Mail
my @IncomingBody = ();              # Body der emfangenen Mail
my $FromAddress = '';               # Adresse des Absenders (From)
my $ReplyAddress = '';              # Adresse des Absenders (Reply-To)
my $Subject = '';                   # Betreffzeile der empf. Mail
my $Number = '';                    # Faxnummer
my $Tmpbase = '/tmp/faxix'.$$;      # Temporaerer Name
my $Tmptext = $Tmpbase . '.txt';    # Name Textdatei
my $Tmpps = $Tmpbase . '.ps';       # Name Postscriptdatei
my $Tmpg3 = $Tmpbase . '.g3.';      # Name G3-Datei(en)

# Eingehende Mail lesen
ReadIncomingMail();

# Abgehenden E-Mail-Text abspeichern
# Dateiname ist die Faxnummer
$Number = $Subject;
$Number =~ s/\D//g;  # alles weg, was nicht Ziffer ist
if (open AUSGABE, ">$Tmptext")
  {
  print AUSGABE @IncomingBody, "\n"; 
  close AUSGABE;
  }

# Nun machen wir ein Postscript-File draus
system($a2psProgram . " -H $Fromaddress $Tmptext > $Tmpps");
unlink($Tmptext);

# Zum Schluﬂ wird das Fax verschickt
if ($HYLA)
  { # Hylafax
  system($Sendfax . " -d ${Fromaddress}\@${Number} $Tmpps");
  unlink($Tmpps);
  }
else
  { # Mgetty/Sendfax
  system($Ghost . " -sOUTPUTFILE=${Tmpg3}\%d $Tmpps");
  system($Sendfax . " -n $Number ${Tmpg3}\*");
  unlink($Tmpps);
  unlink($Tmpg3 . '*');
  }

# --------------------------------------------------------------------- 
#  Unterprogramme
# --------------------------------------------------------------------- 
# Ueber STDIN eingehende Mail zerlegen in Header und Body
# Extrahieren einiger Header-Eintraege:
#     @IncomingHeader: Header der emfangenen Mail
#     @IncomingBody:   Body der emfangenen Mail
#     $FromAddress:    Adresse des Absenders (From)
#     $ReplyAddress:   Adresse des Absenders (Reply-To)
#     $Subject:        Betreffzeile der empf. Mail
sub ReadIncomingMail
  {
  my $InHeader = 1;           # Innerhalb des Headers der Mail = 1, sonst 0
  my $InReceived = 0;         # Innerhalb eines Receoved-Blocks des Headers = 1
  my $TransferEncoding = '';  # MIME-Type
  my $MimeBoundary = undef;   # MIME-Boundary
  my $line = '';              # Zeile fuer die Bearbeitung
  my $hilf = '';              # Hilfsvariable

  while (<STDIN>)
    {
    $line = $_;
    if ($InHeader)
      {
      # Fortsetzungszeile
      if ($line =~ /^ [ \t]/)
        { push(@IncomingHeader, $line) unless $InReceived; }
      else
      # neue Zeile
        {
        # "Received"-Zeilen vernichten
        $InReceived = ($line =~ /^Reveived\:/i)?1:0;

        # "Subject"-Zeile parsen
        if ($line =~ /^Subject\:/i)
          {
          $Subject = $line;
          $Subject =~ s/^Subject: //;
          $Subject = "Re: " . $Subject unless ($Subject =~ /Re\:/i)
          }

        # "From"-Zeile fuer Absender parsen
        $FromAddress = GrabEmail($line) if ($line =~ /^From\:/i);

        # "Reply-To"-Zeile fuer Absender parsen 
        # (ueberschreibt ggf. die "From"-Adresse)
        $ReplyAddress = GrabEmail($line) if ($line =~ /^Reply-To\:/i);

        # Transfer-Encoding feststellen
        if ($line =~ /^Content-Transfer-Encoding\:/i)
          {
          $hilf = $line;
          $hilf =~ s/: /:/;
          ($hilf,$TransferEncoding) = split(/\:/, $hilf);
          ($TransferEncoding,$hilf) = split(/\n/, $TransferEncoding);
          }

        # MIME-Boundary feststellen
        ($hilf, $MimeBoundary) = split(/\"/, $line) if ($line =~ /boundary\=/i);
      
        # Wenn Leerzeile --> Header zuende
        $InHeader = 0 if ($line =~ /^\n/);

        # Zeile speichern, wenn nicht "Received"
        push(@IncomingHeader, $line) unless $InReceived; 
        }
      }
    else # $InHeader = 0 --> Wir befinden uns im Body
      {
      # Sonderbehandlung Quoted-Printable
      if ($TransferEncoding =~ /quoted-printable/i)
        {
        $line =~ s/\=\n/\n/;  # "=" am Zeilenende weg
        $line =~ s/\=([a-fA-F0-9][a-fA-F0-9])/pack("C",hex($1))/eg;
        }

      # Bei Multipart-MIME ggf. wieder den Zwischenheader bearbeiten
      if (defined($MimeBoundary))
        { $InHeader = ($line =~ /$MimeBoundary/)?1:0; }

      # Zeile abspeichern, base64-codierte Attachments wegwerfen
      push(@IncomingBody, $line) unless ($TransferEncoding =~ /base64/i);
      }
    }
  }

# E-Mail-Adresse aus der Parameter-Zeile extrahieren
sub GrabEmail
  {
  $_[0] =~ /([\w\.\-\_]+\@[\w\.\-\_]+)/s;
  return $1;
  }

