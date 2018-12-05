from distutils.core import setup, Extension

xxhash_module = Extension('xxhash',
                                       sources=['xxhash.c', 'speedup_performance.c'])

setup(name='SpeedupPerformance',
      description='xxhash',
      ext_modules=[xxhash_module],
)
