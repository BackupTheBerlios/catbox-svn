#!/usr/bin/perl -w

use Socket;

$ip_string = $ARGV[0] || die "usage: $0 ipaddr";

$ip = inet_aton($ip_string);
$host = (gethostbyaddr($ip, AF_INET))[0];
print "$host\n" if (defined($host));
