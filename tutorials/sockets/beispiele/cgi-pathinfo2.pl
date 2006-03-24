#!/usr/bin/perl
#Zustandserhaltung mit PATH_INFO.

use strict;
use CGI qw(:standard);

use constant INITSTATE => 1;

my $state      = retrieve_state();
my $nextstate  = compute_next_state($state);
my $saveaction = save_state($nextstate);

# Tue etwas abhaengig von $state:
print header;
print start_html('Status mit Pathinfo');
print '<B>Zustand: ', $state,'</B><P>';
print $saveaction;
print end_html;


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
  my $send_me_back = a({-href => url() . "/$newstate"}, , " [Weiter] ");
  return $send_me_back;
  }
