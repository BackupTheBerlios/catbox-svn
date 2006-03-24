#!/usr/bin/perl -w
 
my $host = $ARGV[0] || die "usage: $0 hostname";

my ($name, $aliases, $addrtype, $length, @addrs) = 
    gethostbyname($host);

foreach $i (@addrs) 
  {
  my ($a, $b, $c, $d) = unpack('C4', $i);
  print "$a.$b.$c.$d\n";
  }
