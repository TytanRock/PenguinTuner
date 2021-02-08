project('penguintuner', 'c', version: '0.3.2')
cc = meson.get_compiler('c')
gnome = import('gnome')

if meson.is_cross_build()
	architecture = meson.get_cross_property('host_arch')
else
	architecture = 'amd64' # Default to amd64 arch
endif

gtkdep = dependency('gtk+-3.0')
curldep = dependency('libcurl')

src = [	'src/application.c', 
	'src/robot_controller.c', 
	'src/can_devices.c', 
	'src/app_callbacks.c']

inc = include_directories(['include',
                           'backend/headers'])

backend = 'backend/lib' / architecture / 'libPenguin_Backend.so'

gresources = gnome.compile_resources(	'app_resources_ui', 
					'src/app_resources_ui.gresource.xml',
					source_dir: 'src')

install_data(backend, install_dir: 'lib')

executable(meson.project_name(), 
           gresources, 
           src, 
           include_directories : inc, 
           dependencies : [gtkdep, curldep],
           install: true,
           install_dir: 'bin',
           objects: backend)

