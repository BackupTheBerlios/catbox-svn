#!/usr/bin/perl
#Zustandserhaltung mit Cookies.

use strict;
use CGI qw(:standard);
use CGI::Cookie;

use constant INITSTATE => 1;

my $state      = retrieve_state();
my $nextstate  = compute_next_state($state);
my $saveaction = save_state($nextstate);

# Tue etwas abhaengig von $state:
print header(-cookie => $saveaction);
print start_html('Status mit Cookies');
print '<B>Zustand: ', $state,'</B><P>';
print "Bitte 'Reload Page' bet&auml;tigen";
print end_html;

sub retrieve_state 
  {
  my $state = cookie(-name => 'state') || INITSTATE;
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
  my $cookie   = new CGI::Cookie(-name    => 'state',
				                 -value   => $newstate,
			                     -expires => '+5m');
  return $cookie;
  }
