project('PenguinTuner', 'c')
cc = meson.get_compiler('c')
gnome = import('gnome')

backend_dir = join_paths(meson.source_root(), 'backend/lib/linux-x64')

gtkdep = dependency('gtk+-3.0')
curldep = dependency('libcurl')
backend = cc.find_library('Penguin_Backend', 
                          dirs : backend_dir,
                          required : true)

src = [	'src/application.c', 
	'src/robot_controller.c', 
	'src/can_devices.c', 
	'src/app_callbacks.c']

inc = include_directories([	'include', 
				'backend/headers'])

gresources = gnome.compile_resources(	'app_resources_ui', 
					'src/app_resources_ui.gresource.xml',
					source_dir: 'src')
executable(meson.project_name(), gresources, src, include_directories : inc, dependencies : [gtkdep, curldep, backend])

