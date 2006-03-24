#!/usr/bin/perl
# Verwendung: $0 remote_host [S|D]

use strict;
use IO::Socket;

# --------------- Konfiguration --------------------

use constant TIMEOUT => 5;
use constant MYPORT => 1860;
# use constant PASSWD => "lassmichrein";
use constant PASSWD => "";

# --------------------------------------------------

my $nmap     = "/usr/bin/nmap -sT";      # das müssen wir zentral machen

# --------------------------------------------------

my $sock = '';
my $reply = '';
my $line = '';

my $server = $ARGV[0];

$sock = new IO::Socket::INET(PeerAddr => $server,
			     PeerPort => MYPORT,
			     Proto    => 'tcp', Timeout => TIMEOUT)
    or die "can't connect to $server: $@\n";

print "Connected to $server\n";
$reply = <$sock>;
exit (1) unless ($reply =~ /^Observer/);
$reply = <$sock>;
exit (1) unless ($reply =~ /^AUTH/);
print $sock PASSWD,"\n";
$reply = <$sock>;
exit (2) unless ($reply =~ /^OK/);
if ($ARGV[1] eq 'S') 
  { 
  print $sock "STAT\n"; 
  }
else
  { 
  print $sock "DYNA\n"; 
  }
while (defined($reply = <$sock>))
  {
  print $reply;
  }
$sock->close() if defined $sock;

# jetzt Ports scannen
open DAT,"$nmap $server |";
while ($line = <DAT>)
  {
  print $sock "nmap: $line" if ($line =~ /^[0-9]/);
  }
close(DAT);
