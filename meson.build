project('penguintuner', 'c', version: '0.4.2')
cc = meson.get_compiler('c')
gnome = import('gnome')

if meson.is_cross_build()
	architecture = meson.get_cross_property('host_arch')
else
    architecture = get_option('architecture') 
endif

gtkdep = dependency('gtk+-3.0')

src = [	'src/application.c', 
	'src/robot_controller.c', 
	'src/can_devices.c', 
	'src/app_callbacks.c']

inc = include_directories(['include',
                           'backend/headers'])

backend = 'backend/lib/' + architecture + '/libpenguinbackend.so'

gresources = gnome.compile_resources(	'app_resources_ui', 
					'src/app_resources_ui.gresource.xml',
					source_dir: 'src')

install_data(backend, install_dir: 'lib')

executable(meson.project_name(), 
           gresources, 
           src, 
           include_directories : inc, 
           dependencies : [gtkdep],
           install: true,
           install_dir: 'bin',
           objects: backend)

