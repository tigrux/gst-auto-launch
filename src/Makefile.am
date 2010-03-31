AM_CPPFLAGS = $(PROGRAM_CFLAGS)

BUILT_SOURCES = vala.stamp

bin_PROGRAMS = gst-auto-launch

gst_auto_launch_VALASOURCES = \
	auto-pipeline.vala \
	xml-parser.vala \
	task-scanner.vala \
	task.vala \
	gst-auto-launch.vala \
	command.vala \
	commands.vala

gst_auto_launch_SOURCES = \
	$(gst_auto_launch_VALASOURCES:.vala=.c)

gst_auto_launch_LDADD = \
	$(PROGRAM_LIBS)

vala.stamp:
	$(VALAC) -C $(VALAFLAGS) $(gst_auto_launch_VALASOURCES)
	touch $@

EXTRA_DIST = \
	$(gst_auto_launch_VALASOURCES) \
	pipelines.xml \
	vala.stamp
