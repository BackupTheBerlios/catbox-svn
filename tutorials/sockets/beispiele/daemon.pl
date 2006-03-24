#!/usr/bin/perl

$|=1;
use strict;

my ($pid, $i);

$pid = fork();
die "cannot fork: $!\n" if ($pid == -1);

# Parent beendet sich 
if ($pid > 0)
  {
  print "Parent exits\n";
  exit(0);
  }
 
# Kindprozess wird von init adoptiert
chdir "/tmp" or die "could not chdir to /tmp: $!\n";

for($i = 0; $i < 100; $i++)
  {
  print "This is the Daemon.\n";
  sleep(5);
  }
