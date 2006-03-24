#!/usr/bin/perl
use strict;

#                          AUTORESPONDER
#                          ~~~~~~~~~~~~~
# Dieses Programm antwortet automatisch auf eingehende E-Mails.
# Dabei kann der Antworttext in einer beliebigen Datei gespeichert
# werden. Der Dateiname und -Pfad wird als Kommandozeilenparameter
# uebergeben. Wird keine Datei angegeben, entnimmt das Programm
# den Text einer vorgegebenen Standard-Datei.
#
# Steht im Antworttext irgendwo eine Zeile mit dem Text [COPY_EMAIL] 
# (einschl. der eckigen Klammern), wird an dieser Stelle der quotierte
# Text der Originalmail eingefuegt.
#
# Das Programm entnimmt die Zieladresse der automatischen Antwort dem
# Header der Originalmail. wobei "Reply-To" Vorrang vor "From" hat.
#  
# Um den Autoresponder einzusetzen kann die Datei /etc/aliases auf dem
# Mailserver geaendert werden. Fuegen Sie die folgende Zeile ein ("user"
# steht fuer einen beliebigen Usernamen):
#
# user: "| /path/to/autoresponder.pl /path/to/ResponseFile"
#                              oder
# user: "| /path/to/autoresponder.pl /path/to/ResponseFile", \user
#
# wenn die eingehende Mail auch in der normalen Mailbox gespeichert werden
# soll. Bei der ersten Variante wird die eingehende Mail verworfen 
# (Anwendung z. B. wenn ein User nicht mehr existiert).
# Vergessen Sie anschliessend den Aufruf von "newaliases" nicht!
#
# Nach dem gleichen Schema kann auch in der Datei ".forward" im Home-
# Directory eines Users verfahren werden - es sind dann keine 
# Administrator-Rechte noetig.
#
# Folgende Variablen muessen vor Inbetriebnahme konfiguriert werden:
# ---------------------------------------------------------------------
# Pfad zum sendmail-Programm
my $MailProgram = '/usr/lib/sendmail -t';

# Absender-Email-Adresse der automatischen E-Mail
my $OutgoingFrom = 'postmaster@host.domain';

# Pfad und Name der Datei mit der Default-Antwort
my $StdResponseFile = '/opt/autoresponder/stdresponse';

# ---------------------------------------------------------------------
############## AB HIER MUSS NICHTS MEHR GEAENDERT WERDEN ##############

my @IncomingHeader = ();            # Header der emfangenen Mail
my @IncomingBody = ();              # Body der emfangenen Mail
my $FromAddress = '';               # Adresse des Absenders (From)
my $ReplyAddress = '';              # Adresse des Absenders (Reply-To)
my $Subject = '';                   # Betreffzeile der empf. Mail
my $ResponseFile = '';              # Datei mit dem Antworttext
my @OutgoingEmail = ();             # Ausgehende E-Mail

# Antwortdatei lesen - falls diese nicht lesbar ist, wird
# automatisch die Standard-Antwort genommen
if ($ARGV[0]) { $ResponseFile = $ARGV[0]; }
else          { $ResponseFile = $StdResponseFile; }
if (open RESPONSE, $ResponseFile)
  {
  @OutgoingEmail = <RESPONSE>;
  close RESPONSE;
  }
elsif (open RESPONSE, $StdResponseFile)
  {
  @OutgoingEmail = <RESPONSE>;
  close RESPONSE;
  }

# Eingehende Mail lesen
ReadIncomingMail();

# Jetzt weg mit der Mail
if (ValidEmail($ReplyAddress))
  { SendOutgoingMail($ReplyAddress,$Subject); }
elsif (ValidEmail($FromAddress))
  { SendOutgoingMail($FromAddress,$Subject); }

########## Unterprogramme ##########

# Abgehende E-Mail zusammenbasteln und wegschicken
# Global: @OutgoingEmail, @IncomingBody
sub SendOutgoingMail
  {
  my $line = '';             # Zeile fuer die Bearbeitung
  my $From = $_[0];          # 1. Parameter: Zieladresse
  my $Subj = $_[1];          # 2. Parameter: Betreff
  open MAIL,"|$MailProgram\n";
  print MAIL "From: $OutgoingFrom\n";
  print MAIL "Content-Type: text/plain; charset=iso-8859-1\n";
  print MAIL "Content-Transfer-Encoding: 8bit\n";
  print MAIL "Comment: AUTOMATISCHE ANTWORT - AUTOMATIC ANSWER\n";
  print MAIL "To: $From\n";
  print MAIL "Subject: $Subj\n";
  print MAIL "\n";
  foreach $line (@OutgoingEmail)
    {
    chomp($line);
    if ($line =~ /\[COPY\_EMAIL\]/)
      {
      map {$_ = '> ' . $_} @IncomingBody;  # Quoting
      print MAIL "\n", @IncomingBody, "\n"; 
      }
    else
      { print MAIL $line, "\n"; }
    }
  close MAIL;
  }
  
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

# Stellt der Parameter eine gueltige E-Mail-Adresse dar?
sub ValidEmail
  {
  return 0 if $_[0] =~ /(?:[\.\-\_]{2,})|(?:@[\.\-\_])|(?:[\.\-\_]@)|(?:\A\.)/;
  return 1 if $_[0] =~ /^[\w\.\-\_]+\@\[?[\w\.\-\_]+\.(?:[\w\.\-\_]{2,3}|[0-9])\]?$/;
  return 0;
  }

