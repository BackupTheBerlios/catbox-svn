#!/usr/bin/perl

# Die folgenden Variablen muessen an die lokale Konfiguration angepasst werden.

# Zeichenkette(n), die in der Protokollzeile auftauchen muessen.
#
# Sie koennen auch mehrere Strings angeben, z. B. 
# $include="laber/eins|laber/zwei";
#
# $include = "ALL"; nimmt alle Protokollzeilen, mit Ausnahme der
# durch $exclude ausgeschlossenen.

$include="ALL";            


# Protokollzeilen, die diese Strings enthalten, werden bei der Berechnung der 
# Statistik ausgeschlossen (hier: Graphiken und Aufrufe von CGI Programmen).
#
# Mehrere Strings wieder durch "|" trennen.

$exclude = "gif|jpg|png|cgi";

# Name und Pfad der Webserver-Logdatei

$LOGDATEI = "/var/log/any-access_log"; 

# Farbe der Balken fuer die Stundenstatistik
$scolor = "#FFFF00";

# Farbe der Balken fuer die Tagesstatistik
$wcolor = "#FF00FF";

# Das wars! Ab hier muss nichts mehr geaendert werden!
###########################################################################

&datum;
&open_logfile;
&calc_access;
&kopf;
&general;
&by_hour;
&by_date;
&by_html;
&fuss;

##########################################################################

# Open the SERVER LOG FILES
# -------------------------
sub open_logfile 
  {
  open (LOG,"$LOGDATEI") || die "Kann $LOGDATEI nicht oeffnen!\n";
  while ($line = <LOG>) 
    { 
    chomp($line);
    if ((($line =~ /$include/) || ($include eq "ALL")) && ($line !~ /$exclude/i))
      { push(@lines,$line); } 
    }
  close(LOG);
  }


# Extract the data from each line of the log
# ------------------------------------------

sub calc_access 
  {
  $i = 0; 
  $currentdate = "";
   foreach (@lines) 
     {
     ($site,$junk1,$junk2,$when,$junk3,$junk4,$page,$junk5,$number,$bytes) = split;
     $page=~ s/%7E/~/gi;
     ($date,$hour,$minute,$second)=split(':',$when);
     $hour=~ s/^0//;
     # Wenn das Datum gleichbleibt, erhohe fuer dieses Datum den Counter um eins
     if ($date eq $currentdate)
        { $counter[$i]++; }
      # Nachster Tag (Tageszaehler ist die Variable $i)
     else 
       { 
       $i++;
       $currentdate=$date;
       $counter[$i]++;
       }
     ($firstdate) || ($firstdate=$date);
     ($day,$month,$year) = split('/',$date);
     $date = "$year/$month/$day";
     $date=~ s/\[//;
     $dates{$date}++;   # Anzahl Zugriffe pro Tag
     $hours{$hour}++;   # Anzahl Zugriffe pro Stunde 
     $pages{$page}++;   # Anzahl Zugriffe pro FILE
     $totalbytes = $totalbytes + $bytes;
     }
   if ($totalbytes < 10)
     {
     print "<html><head><title>Keine Abrufe f&uuml;r $include.</title></head>\n";
     print "<body><h1 align=center>Keine Abrufe f&uuml;r $include.</h1>\n";
     print "F&uuml;r das Verzeichnis (die Verzeichnisse) <b>$include</b> wurden\n",
     print "im letzten Monat keine Abrufe verzeichnet.\n";
     print "</body></html>\n";
     exit;
     }
  }
   
sub kopf 
  {
  print "<HTML>\n";
  print "<head><title>Zugriffs-Statistik</title></head>\n";
  print "<body bgcolor=\"#ffffff\" text=\"#000000\" link=\"#0000ff\" vlink=\"#cc00cc\">\n";
  if ($include eq "ALL")
    { print "<H2 ALIGN=CENTER>Zugriffstatistik</H2>\n"; }
  else
    { print "<H2 ALIGN=CENTER>Zugriffstatistik f&uuml;r $include</H2>\n"; }
  print "<H4 ALIGN=CENTER>$long_date</H4>\n";
  }

sub general 
  {
  $firstdate=~ s/\[//;
  $firstdate =~ s/^0//;
  print "<H2>Allgemeine Daten</H2>\n";
  print "<B>Auswertungszeitraum:</B> $firstdate bis $date_2<BR>\n";
  print "<B>Gesamtzahl aller Zugriffe:</B> $#lines <BR>\n";
  print "<B>Gesamtvolumen (in Bytes):</B> $totalbytes <BR>\n";
  }

# Calculate stats by hour
# -----------------------
sub by_hour 
  {
  print "<H2 ALIGN=CENTER>Zugriffsstatistik nach Tageszeit</H2>\n";
  print "<TABLE BORDER=1 CELLPADDING=3 ALIGN=CENTER><TR><TD>\n";
  print "<TABLE BORDER=0 CELLPADDING=3 ALIGN=CENTER>\n<TR>";
  $highest=0;
  # ermittle maximale Anzahl von Zugriffen zu einer Stunde
  foreach $key (keys %hours) 
    {
    if ($hours{$key} > $highest) 
      { $highest=$hours{$key}; }
    }
  foreach $key (keys %hours) 
    {
    $barsize{$key} = int(($hours{$key} * 250) / $highest);
    }
  foreach $key (0..23) 
    {
    if ($barsize{$key} < 2)
      { $barsize{$key} = 2; }
    print "<TD ALIGN=CENTER VALIGN=BOTTOM>\n";
    print "<I>$hours{$key}</I><BR>\n";
    # Balken wird als einspaltige Tabelle mit variabler Hoehe realisiert
    print "<TABLE BORDER=0 BGCOLOR=\"$scolor\" HEIGHT=$barsize{$key} WIDTH=10>\n";
    print "<TR><TD>\&nbsp;</TD></TR></TABLE>\n";
    print "</TD>\n";
    }
  print "</TR>\n<TR>\n";
  foreach $key (0..23) 
    {
    print "<TH ALIGN=CENTER>$key</TH>\n"; 
    }
  print "</TR>\n<TR>\n";
  print "<TH ALIGN=CENTER colspan=24>Uhrzeit</TH>\n"; 
  print "</TR>\n";
  print "</TABLE>\n";
  print "</TD></TR></TABLE>\n<P>\n";
  }
   
# Calculate stats by Date
# -----------------------
sub by_date 
  {
  $highest=0;
  undef %barsize;
  foreach $key (keys %dates) 
    {
    if ($dates{$key} > $highest)
      { $highest=$dates{$key}; }    
    }
  foreach $key (keys %dates) 
    {
    $barsize{$key} = int(($dates{$key} * 350) / $highest);
    }
  print "<H2 ALIGN=CENTER>Abrufstatistik der letzten 30 Tage</H2>\n";
  print "<TABLE BORDER=1 CELLPADDING=3 ALIGN=CENTER><TR><TD>\n";
  print "<TABLE ALIGN=CENTER BORDER=0 CELLPADDING=3>\n";
  foreach $tag (sort {$a cmp $b} (keys %dates))
    {
    print "<TR><TD ALIGN=RIGHT VALIGN=MIDDLE><TT>$tag</TT></TD>\n";
    print "<TD><B>$dates{$tag}</B></TD>\n";
    print "<TD ALIGN=LEFT VALIGN=MIDDLE>\n";
    # Balken wird als einzeilige Tabelle mit variabler Breite realisiert
    print "<TABLE BORDER=0 BGCOLOR=\"$wcolor\" HEIGHT=20 WIDTH=$barsize{$tag}>\n";
    print "<TR><TD>\&nbsp;</TD></TR></TABLE></TD>\n";
    print "</TR>\n";
    }
  print "</TABLE>\n";
  print "</TD></TR></TABLE>\n<P>\n";
  }

# Information on accessed HTML-pages
# ----------------------------------
sub by_html 
  {
  print "<H2 ALIGN=CENTER>Zugriffe pro HTML-Seite</H2>\n"; 
  print "<TABLE BORDER=1 CELLPADDING=3>\n";
  # sortiere die WWW-Seiten vor der Augabe
  foreach $page (sort(keys %pages))
    {
    $page=~ s/[\<\>]//g;
    print "<TR><TD>&nbsp;<a href=$page>$page</a>&nbsp;</TD>";
    print "<TD><B>&nbsp;$pages{$page}&nbsp;</B></TD></TR>\n";
    }
  print "</TABLE>\n<P>\n";
  }

sub fuss 
  {
  print "</body>\n";
  print "</html>\n";
  }

sub datum 
  {
  ($sec,$min,$hour,$mday,$mon,$year,$wday,$yday,$isdst) = localtime(time);
  if ($sec < 10) { $sec = "0$sec"; }
  if ($min < 10) { $min = "0$min"; }
  if ($hour < 10) { $hour = "0$hour"; }
  if ($mon < 10) { $mon = "0$mon"; }
  if ($mday < 10) { $mday = "0$mday"; }
  $month = $mon + 1;
  $year = $year + 1900;
  @months1 = ("Januar","Februar","M&auml;rz","April","Mai","Juni","Juli","August","September","Oktober","November","Dezember");
  @months2 = ("Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec");
  $date_1 = "$mday.$month $year";
  $date_2 = "$mday/$months2[$mon]/$year";
  $long_date = "$mday\. $months1[$mon] $year ($hour\.$min Uhr)";
  }