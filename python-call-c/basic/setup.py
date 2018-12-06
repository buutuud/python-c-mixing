from distutils.core import setup, Extension

xxhash_module = Extension('xxhash',
                                       sources=['xxhash.c', 'py_xxhash.c'])

setup(name='SpeedupPerformance',
      description='xxhash',
      ext_modules=[xxhash_module],
)
