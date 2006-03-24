#!/usr/bin/perl
# Zustandserhaltung mit PATH_INFO ohne CGI-Modul.

use strict;

use constant INITSTATE => 1;

my $url = $ENV{'SERVER_NAME'} . $ENV{'SCRIPT_NAME'};
my $state      = retrieve_state();
my $nextstate  = compute_next_state($state);
my $saveaction = save_state($nextstate);

# Tue etwas abhaengig von $state:
print "Content-type: text/html\n\n";
print "<HTHL>", "\n";
print "<HEAD><TITLE>Status mit Pathinfo</TITLE></HEAD>\n";
print "<BODY>\n";
print "<B>Zustand: ", $state,"</B><P>";
print $saveaction;
print "</BODY></HTML>\n";


sub retrieve_state 
  {
  my $state = $ENV{'PATH_INFO'} || INITSTATE;
  $state =~ s/^\///;
  return $state;
  }

sub compute_next_state 
  {
  my $current_state = shift;
  return $current_state + 1;
  }

sub save_state 
  {
  my $newstate = shift;
  my $send_me_back = "<A HREF=\"http://$url/$newstate\"> [Weiter] </A>";
  return $send_me_back;
  }
