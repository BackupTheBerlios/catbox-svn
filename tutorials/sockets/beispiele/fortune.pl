#!/usr/bin/perl

use strict;

$/ = "\n%\n";

my ($data,$cookie);

$data = '/usr/share/fortune/fortunes';
$data = $ARGV[0] if (defined($ARGV[0]));
srand($$);
open(KEKS,"$data") || die "Keine Kekse\n";
rand($.) < 1 && ($cookie = $_) while <KEKS>;
$cookie =~ s/%$//;
print "\n$cookie\n";
close(KEKS);

