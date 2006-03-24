#!/usr/bin/perl
# Fortune-Server

use strict;
use IO::Socket;

use constant MYPORT => 2000;
use constant DATA => '/usr/share/fortune/fortunes';

my $sock = '';
my $client = '';

$sock = new IO::Socket::INET(LocalPort => MYPORT,
		             Reuse     => 1,
		             Listen    => 5)
    or die "can't create local socket: $@\n";

$SIG{'CHLD'} = sub { wait(); };    # Zombies verhindern

print "Accepting connections on Port ", MYPORT, "...\n";
while ($client = $sock->accept()) 
  {
  # Verbindung ist aufgebaut
  print "Accepted connection from ",
        $client->peerhost(), ":", $client->peerport(), "\n";

  # Erzeugen eines Kindprozesses und Uebergabe an $client.
  if (fork() == 0) # Kindprozess 
    {
    $sock->close; # not needed in child
    # Jetzt kommt der Spruch
    $/ = "\n%\n";
    my $cookie;

    srand($$);
    open(KEKS,DATA) || die "Keine Kekse\n";
    rand($.) < 1 && ($cookie = $_) while <KEKS>;
    $cookie =~ s/%$//;
    print $client "\n$cookie\n";
    close(KEKS);
    $client->close;
    exit 0;
    }
   $client->close; # not needed in parent
   }
