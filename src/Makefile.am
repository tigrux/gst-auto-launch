AM_CPPFLAGS = $(PROGRAM_CFLAGS)

BUILT_SOURCES = vala.stamp

bin_PROGRAMS = gst-auto-launch

gst_auto_launch_VALASOURCES = \
	auto-pipeline.vala \
	config-parser.vala \
	gst-auto-launch.vala \
	object-list.vala \
	commands.vala

gst_auto_launch_SOURCES = \
	$(gst_auto_launch_VALASOURCES:.vala=.c)

gst_auto_launch_LDADD = \
	$(PROGRAM_LIBS)

vala.stamp: $(gst_auto_launch_VALASOURCES)
	$(VALAC) -C $(VALAFLAGS) $(gst_auto_launch_VALASOURCES)
	touch $@

EXTRA_DIST = \
	$(gst_auto_launch_VALASOURCES) \
	config.xml \
	vala.stamp
