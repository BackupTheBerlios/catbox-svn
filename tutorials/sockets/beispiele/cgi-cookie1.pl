#!/usr/bin/perl
#Zustandserhaltung mit Cookies.

use strict;

use constant INITSTATE => 1;

my $url = $ENV{'SERVER_NAME'} . $ENV{'SCRIPT_NAME'};
my $Cookie_Domain = $ENV{'SERVER_NAME'};
my $ExpDate = "Monday, 31-Dec-2035 23:59:59 GMT"; # cookie expire date

my $state      = retrieve_state();
my $nextstate  = compute_next_state($state);
save_state($nextstate);

# Tue etwas abhaengig von $state:
print "Content-type: text/html\n\n";
print "<HTHL>", "\n";
print "<HEAD><TITLE>Status mit Cookies</TITLE></HEAD>\n";
print "<BODY>\n";
print '<B>Zustand: ', $state,'</B><P>';
print "Bitte 'Reload Page' bet&auml;tigen";
print "</BODY></HTML>\n";

sub retrieve_state 
  {
  # must be before "content-type"-line
  my $state = &GetMakeCookie;
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
  SetCookie("State", $newstate, $ExpDate, "/", $Cookie_Domain);
  }

sub SetCookie
  {
  my ($name, $val, $exp, $path, $dom) = @_;
  print "Set-Cookie: ";
  print "$name=$val, expires=$exp, path=$path, domain=$dom\n";
  }

sub GetCookies
  {
  my %cookies;
  my $cookie;
  foreach $cookie (split (/; /,$ENV{'HTTP_COOKIE'}))
    {
    my($key) = split(/=/, $cookie);
    $cookies{$key} = substr($cookie, index($cookie, "=")+1);
    }
  return(%cookies);
  }

sub GetMakeCookie
  {
  my $State = '';
  my %Cookies = GetCookies();
  $State = $Cookies{'State'};
  $State =~ s/,.*//;
  # No Cookie Data? Establish one!
  if ($State eq '')
    {
    $State = INITSTATE;
    SetCookie("State", $State, $ExpDate, "/", $Cookie_Domain);
    }
  return($State);
  }   
