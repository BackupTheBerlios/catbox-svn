#!/usr/local/bin/perl -w
# udp-client.pl -- UDP-Client fragt Zeit des angegebenen Hosts ab.
# Die Antwort ist ein 4 Byte-Wert in Network-Byte-Order,
# der die Zeit in Sekunden seit dem 1.1.1900 (nicht 1970!) angibt.

use constant SECS_OF_70_YEARS => 2208988800;

use Socket;
use IO::Socket;                 # Standardmodul
use strict;

my ($src, $answer, $rt, $remotehost);

# Wir erzeugen einen "unconnected" UDP-Socket:
$sock = new IO::Socket::INET(Proto => 'udp')
    or die "can't create UDP Socket: $!\n";

# Zieladresse im Binaerformat
my $hostname = @ARGV[0]; 
my $port     = getservbyname('time', 'udp');
my $ipaddr   = gethostbyname($hostname);
my $remaddr  = sockaddr_in($port, $ipaddr);

# Nun senden wir dem Host ein (leeres) Datagramm.
# Das loest bei dem time/udp-Server eine Antwort aus.
die "can't send to $hostname\n"
     unless defined $sock->send("", 0, $remaddr);

# Hinweis: Wenn der Host nicht antworten oder seine Antwort
# verloren geht, dann bleibt recv()s haengen. 
# In diesem Fall mit CTRL-C abbrechen!
$src = $sock->recv($answer, 4, 0) || die "can't recv(): $!\n";
$remotehost = gethostbyaddr((sockaddr_in($src))[1], AF_INET);
$rt = unpack("N", $answer) - SECS_OF_70_YEARS;
print "$remotehost: ", scalar(localtime($rt)), "\n";
