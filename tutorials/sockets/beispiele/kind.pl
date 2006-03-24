#!/usr/bin/perl

use POSIX ":sys_wait_h";
use strict;

my ($i, $pid, $time);
my %child_pids = ();

$|=1;

$SIG{CHLD} = sub 
  {
  my($pid);
  foreach $pid (keys(%child_pids))
    {
    if(waitpid($pid,WNOHANG))
      {
      print "Terminated: $pid\n";
      delete $child_pids{$pid};
      }
    }
  };

# Machen wir mal 10 Kinder
for($i = 0; $i < 10; $i++)
  {
  $pid = fork();
  if($pid == 0) # KIND
    {
    sleep rand(20);
    exit(0);
    }
  else          # ELTERN
    {
    print "$pid wurde gestartet\n";
    $child_pids{$pid} = 1; # merken
    }
  }

# Warten, bis alle Kinder terminiert sind
$time = 0;
while(0 + keys(%child_pids)) 
  {
  print "TIME: $time\n";
  sleep 1;
  $time++;
  }
