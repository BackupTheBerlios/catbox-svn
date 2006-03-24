#!/usr/local/bin/perl -w
# tcp-client.pl -- Ein einfacher TCP-Client.
#                  Verwendung: $0 remote_host remote_port [theystart]

use IO::Socket;

use constant TIMEOUT => 5;
$sock = new IO::Socket::INET(PeerAddr => $ARGV[0],
			     PeerPort => $ARGV[1],
			     Proto    => 'tcp', Timeout => TIMEOUT)
    or die "can't connect to $ARGV[0]:$ARGV[1]: $@\n";

# Wer faengt zuerst an? Ist ein drittes Argument da, fangen wir an,
# sonst faengt der Server an.
if (defined $ARGV[2]) {
    print "Server:> $reply" if defined($reply = <$sock>);
}

# Das ist die normale Lese/Schreib-Schleife.
while (<STDIN>) {
    print $sock $_;
    last unless defined($reply = <$sock>);
    print "Server:> $reply";
}

$sock->close() if defined $sock;      # Das war's.
