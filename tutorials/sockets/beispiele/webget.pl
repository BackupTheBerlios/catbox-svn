#!/usr/bin/perl

# Fordert ein durch URL angegebenes Dokument an.

use LWP::Simple;                # Aus dem CPAN: libwww-perl

print get($ARGV[0]);            # Seite anfordern und ausdrucken
