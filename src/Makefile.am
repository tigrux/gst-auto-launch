AM_CPPFLAGS = $(PROGRAM_CFLAGS)

bin_PROGRAMS = gst-auto-launch

gst_auto_launch_VALASOURCES = \
	auto-pipeline.vala \
	config-parser.vala \
	gst-auto-launch.vala \
	object-list.vala \
	commands.vala

gst_auto_launch_SOURCES = \
	$(gst_auto_launch_VALASOURCES:.gs=.c)

gst_auto_launch_LDADD = \
	$(PROGRAM_LIBS)

EXTRA_DIST = \
	$(gst_auto_launch_VALASOURCES) \
	config.xml
