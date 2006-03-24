#!/usr/bin/perl -w

use Net::DNS;

my $domain = $ARGV[0] || die "usage: $0 domain";
my $resolver = new Net::DNS::Resolver;

# MX-Record abfragen 
my @mxrecs = mx($resolver, $domain);
if (@mxrecs) 
  {
  # Gefunden!
  foreach $rec (@mxrecs) 
    {
    print $rec-&gt;preference, " ", 
           $rec-&gt;exchange, "\n";
    }
  } 
else 
  {
  # Leere Liste, Fehler!
  print "Kein MX-Record f&uuml;r $domain: ", 
          $resolver-&gt;errorstring, "\n";
  }
