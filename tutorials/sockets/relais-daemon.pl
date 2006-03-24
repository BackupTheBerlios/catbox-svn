#!/usr/bin/perl -w
# Server fuer Relaissteuerung

use strict;
use POSIX 'setsid';
use IO::Socket;
use Digest::MD5  qw(md5 md5_hex md5_base64);

my $PORT = 666;
my $PASS= "geheim";

my ($child, $rc, $sock, $client, $tim, $rs, $hs, $p, $com, $res);

# Exit-Handler setzen
$SIG{TERM} = $SIG{INT} = sub { exit(0); };

# Daemon werden
$child = fork();
if ($child < 0) { die "Cannot fork!\n"; }
exit(0) if ($child > 0);          # Eltenprozess beendet sich
&setsid();                        # Abtrennen
open(STDIN, "</dev/null");        # Standarddateien umlenken
open(STDOUT, ">/var/log/relais.log");
open(STDERR, ">&STDOUT");
chdir('/tmp');                    # Arbeitsverzeichnis /tmp
umask(0);                         # UMASK definieren
                                  # Pfad definiert setzen:
$ENV{PATH} = '/bin; /sbin; /usr/bin; /usr/sbin; /usr/local/bin;';

$sock = new IO::Socket::INET(LocalPort => $PORT, 
                             Reuse => 1, 
                             Listen => 5)
          || die "Can't create local socket : $@\n";

# Ins Logfile schreiben (Startmeldung):
print "Accepting connections on port ",$PORT, "...\n";
while ($client = $sock->accept()) 
  {
  # Ins Logfile schreiben:
  print "Accepted connection from ",
        $client->peerhost(), ":", $client->peerport(), "\n";

  $tim = gmtime();
  $rs = substr(rand(),2,4);
  print $client "AUTH\n$tim\n$rs\n";

  next if (<$client> ne (md5_hex($tim, $rs, $PASS))."\n");
  $rc = <$client>; chomp ($rc);
  print $client md5_hex($tim, $rc, $PASS)."\n";

  next if (! defined($com = <$client>));
  chomp ($com);
  print "Commandline: $com\n";           # Ins Logfile 
  $res = `/usr/local/bin/relais $com`;
  print $client "$res\n";
  }
  continue { $client->close(); }
