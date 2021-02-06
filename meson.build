project('penguintuner', 'c', version: '0.3.2')
cc = meson.get_compiler('c')
gnome = import('gnome')

gtkdep = dependency('gtk+-3.0')
curldep = dependency('libcurl')
glibdep = dependency('glib-2.0')

src = [	'src/application.c', 
	'src/robot_controller.c', 
	'src/can_devices.c', 
	'src/app_callbacks.c']

inc = include_directories(['include',
                           'backend/headers'])

backend = 'backend/lib/linux-armv7/libPenguin_Backend.so'

gresources = gnome.compile_resources(	'app_resources_ui', 
					'src/app_resources_ui.gresource.xml',
					source_dir: 'src')
executable(meson.project_name(), 
           gresources, 
           src, 
           include_directories : inc, 
           dependencies : [gtkdep, curldep, glibdep],
           install: true,
           install_dir: '/usr/bin',
           objects: backend)

