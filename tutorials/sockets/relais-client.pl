#!/usr/bin/perl

use strict;

use IO::Socket;
use Digest::MD5  qw(md5 md5_hex md5_base64);

my $SERVER = "blackhole.ee.fhm.edu";
my $PORT = 666;
my $TIMEOUT = 50;
my $PASS= "geheim";

my ($eingabe, $ausgabe, $rs, $com);

my $sock = new IO::Socket::INET(PeerAddr => $SERVER, 
                                PeerPort => $PORT,
	                        Proto    => 'tcp', 
                                Timeout => $TIMEOUT) || die "Can't connect to server: $@\n";

$eingabe = <$sock>; chomp($eingabe);
if ($eingabe ne "AUTH") 
  { print "Authentication failed\n"; close($sock); exit(1); }
$eingabe = <$sock>; chomp($eingabe);
# print "Got: $eingabe\n";
$rs = <$sock>; chomp($rs);
# print "Got: $rs\n";
$ausgabe = md5_hex($eingabe, $rs, $PASS);
print $sock "$ausgabe\n";
# print "Sent: $ausgabe\n";
$ausgabe = substr(rand(),2,4); 
print $sock "$ausgabe\n";
# print "Sent: $ausgabe\n";
$ausgabe = md5_hex($eingabe, $ausgabe, $PASS); 
$eingabe = <$sock>; chomp($eingabe);
# print "Got: $eingabe\n";
if($eingabe ne $ausgabe) 
  { print "Authentication failed\n"; close($sock); exit(1); }
print $sock "@ARGV\n";
$com = <$sock>;
print "Returned $com\n";

