load 'gp/style.gp'
set macros
NOYTICS = "set format y ''; unset ylabel"
YTICS = "set ylabel 'Throughput (Mops/s)' offset 2"
PSIZE = "set size 0.5, 0.6"

set key horiz maxrows 1

set output "eps/fig10_sl.eps"

set terminal postscript color "Helvetica" 24 eps enhanced
set rmargin 0
set lmargin 3
set tmargin 3
set bmargin 2.5

title_offset   = -0.5
top_row_y      = 0.0
bottom_row_y   = 0.0
graphs_x_offs  = 0.1
plot_size_x    = 1.18
plot_size_y    = 0.67

DIV              =    1e6
FIRST            =    2
OFFSET           =    3
column_select(i) = column(FIRST + (i*OFFSET)) / (DIV);

LINE0 = '"herlihy"'
LINE0lf = '"fraser"'
LINE1 = '"herl-optik"'
LINE2 = '"optik1"'
LINE3 = '"optik2"'
LINE4 = '""'

NCOL0 = 0
NCOL0lf = 1
NCOL1 = 4
NCOL2 = 2
NCOL3 = 3

PLOT0 = '"Very-low contention\n{/*0.8(8192 elements, 1% updates)}"'
PLOT1 = '"Low contention\n{/*0.8(4096 elements, 10% updates)}"'
PLOT2 = '"Medium contention\n{/*0.8(2048 elements, 20% updates)}"'
PLOT3 = '"High contention\n{/*0.8(512 elements, 50% updates)}"'
PLOT4 = '"Very-high contention\n{/*0.8(128 elements, 100% updates)}"'

# font "Helvetica Bold"
# set label 1 "Opteron" at screen 0.018, screen 0.18 rotate by 90 font ',30' textcolor rgb "red"
# set label 2 "Xeon"    at screen 0.018, screen 0.66 rotate by 90 font ',30' textcolor rgb "red"


# ##########################################################################################
# XEON #####################################################################################
# ##########################################################################################


FILE0 = '"data/data.sl.i8192.u1.dat"'
FILE1 = '"data/data.sl.i4096.u10.dat"'
FILE2 = '"data/data.sl.i2048.u20.dat"'
FILE3 = '"data/data.sl.i512.u50.dat"'
FILE4 = '"data/data.sl.i128.u100.dat"'

set xlabel "# Threads" offset 0, 0.75 font ",28"
set xtics offset 0,0.4
unset key

set size plot_size_x, plot_size_y
set multiplot layout 5, 2

set origin 0.0 + graphs_x_offs, top_row_y
set size plot_size_x, plot_size_y
set ylabel 'Throughput (Mops/s)' offset 2,0.5
@PSIZE
set lmargin 3
set title @PLOT2 offset 0.2,title_offset font ",28"
plot \
     @FILE2 using 1:(column_select(NCOL0lf)) title @LINE0lf ls 6 with linespoints, \
     "" using 1:(column_select(NCOL0)) title @LINE0 ls 1 with linespoints, \
     "" using 1:(column_select(NCOL1)) title @LINE1 ls 2 with linespoints, \
     "" using 1:(column_select(NCOL2)) title @LINE2 ls 3 with linespoints, \
     "" using 1:(column_select(NCOL3)) title @LINE3 ls 4 with linespoints

set origin 0.53 + graphs_x_offs, top_row_y
@PSIZE
set lmargin 3
set title @PLOT4
@YTICS
set ylabel ""
unset ylabel
plot \
     @FILE4 using 1:(column_select(NCOL0lf)) title @LINE0lf ls 6 with linespoints, \
     "" using 1:(column_select(NCOL0)) title @LINE0 ls 1 with linespoints, \
     "" using 1:(column_select(NCOL1)) title @LINE1 ls 2 with linespoints, \
     "" using 1:(column_select(NCOL2)) title @LINE2 ls 3 with linespoints, \
     "" using 1:(column_select(NCOL3)) title @LINE3 ls 4 with linespoints

unset origin
unset border
unset tics
unset xlabel
unset label
unset arrow
unset title
unset object

#Now set the size of this plot to something BIG
set size 2*plot_size_x, plot_size_y #however big you need it
set origin 0.0, 1.1

#example key settings
# set key box 
#set key horizontal reverse samplen 1 width -4 maxrows 1 maxcols 12 
#set key at screen 0.5,screen 0.25 center top
set key font ",28"
set key spacing 1.5
set key horiz
set key width -3
set key samplen 2.5
set key at screen 0.568, screen 0.65 center top

#We need to set an explicit xrange.  Anything will work really.
set xrange [-1:1]
@NOYTICS
set yrange [-1:1]
plot \
     NaN title @LINE0lf ls 6 with linespoints, \
     NaN title @LINE0 ls 1 with linespoints, \
     NaN title @LINE1 ls 2 with linespoints, \
     NaN title @LINE2 ls 3 with linespoints, \
     NaN title @LINE3 ls 4 with linespoints

#</null>
unset multiplot  #<--- Necessary for some terminals, but not postscript I don't thin
