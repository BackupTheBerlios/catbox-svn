#!/usr/bin/perl
# direktes Verschicken einer E-Mail ueber die 
# Socket-Schnittstelle - Implementierung von SMTP

use strict;
use IO::Socket;

my $result = '';


my $LOCALHOST = 'localhost';
my $SMTP_SERVER = 'mail.ee.fhm.edu';
my $from = 'webmaster@netzmafia.de';
my $rcpt = 'plate@netzmafia.de';
my $subject = 'Test';
my $text = qq~
Hallo Juergen,

wie geht es denn  so?
~;

$result=&sendmail($from, $rcpt, $SMTP_SERVER, $subject, $text); 
print $result, "\n";

sub sendmail
  {
  #  Sample call:
  #
  # &sendmail($from, $to, $smtp-server, $subject, $message );
  #

  my ($fromaddr, $to, $smtp, $subject, $message) = @_;
  my $sock = '';

  $fromaddr =~ s/.*<([^\s]*?)>/$1/; # get from email address
  $message =~ s/^\./\.\./gm;        # handle . as first character
  $message =~ s/\r\n/\n/g;          # handle line ending
  $smtp =~ s/^\s+//g;               # remove spaces around $smtp
  $smtp =~ s/\s+$//g;
  return('no recipient') unless ($to);

  $sock = new IO::Socket::INET(PeerAddr => $smtp,
                               PeerPort => 25,
                               Proto    => 'tcp', 
                               Timeout  => 60)
          or return('cannot open socket');
  $_ = <$sock>;
  if (/^[45]/) { close($sock); return($_); }

  print $sock "HELO $LOCALHOST\n";
  $_ = <$sock>;
  if (/^[45]/) { close($sock); return($_); }

  print $sock "MAIL from: <$fromaddr>\n";
  $_ = <$sock>;
  if (/^[45]/) { close($sock); return($_); }

  foreach (split(/, /, $to))
    {
	print $sock "RCPT to: <$_>\n";
	$_ = <$sock>;
    if (/^[45]/) { close($sock); return($_); }
    }

  print $sock "DATA\n";
  $_ = <$sock>;
  if (/^[45]/) { close $sock; return($_); }

  print $sock "To: $to\n";
  print $sock "From: $fromaddr\n";
  print $sock "X-Mailer: Tralala 1.0\n";
  print $sock "Subject: $subject\n\n";
  print $sock "$message";
  print $sock "\n.\n";

  $_ = <$sock>;
  if (/^[45]/) { close($sock); return($_); }

  print $sock "QUIT\n";
  $_ = <$sock>;
  close($sock);
  return('success');
  }
