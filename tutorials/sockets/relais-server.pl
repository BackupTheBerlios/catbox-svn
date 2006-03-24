#!/usr/bin/perl -w
# Server fuer Relaissteuerung

use strict;
use IO::Socket;
use Digest::MD5  qw(md5 md5_hex md5_base64);

my $PORT = 666;
my $PASS = "geheim";

my ($rc, $sock, $client, $tim, $rs, $hs, $p, $com, $res, %cfg);

$sock = new IO::Socket::INET(LocalPort => $PORT, 
                             Reuse => 1, 
                             Listen => 5)
                             || die "Can't create local socket : $@\n";

print "Accepting connections on port ",$PORT, "...\n";
while ($client = $sock->accept()) 
  {
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
  print "Commandline: $com\n";  
#  $res = "OK: 007";
  $res = `/usr/local/bin/relais $com`;
  print $client "$res\n";
  }
  continue { $client->close(); }
