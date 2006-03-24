#!/usr/bin/perl
# Zustandserhaltung mit QUERY_STRING.

use strict;
use CGI qw(:standard);

use constant INITSTATE => 1;

my $state      = retrieve_state();
my $nextstate  = compute_next_state($state);
my $saveaction = save_state($nextstate);

# Tue etwas abhaengig von $state:
print header;
print start_html('Status mit Query-String');
print '<B>Zustand: ', $state,'</B><P>';
print $saveaction;
print end_html;


sub retrieve_state 
  {
  my $state = param('state') || INITSTATE;
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
  my $send_back = a({-href => url() . "?state=$newstate"}, " [Weiter] ");
  return $send_back;
  }

