def configuration(parent_package='', top_path=None):
    from numpy.distutils.misc_util import Configuration
    config = Configuration('', parent_package,top_path)
    config.add_extension('LAPJV', ['pyLAPJV.cpp', 'lap.cpp', 'lap.h'])
    return config

if __name__ == "__main__":
    from numpy.distutils.core import setup
    setup(configuration=configuration,
          name='pyLAPJV',
          version='0.3.2',
          url='http://github.com/hrldcpr/pyLAPJV',
          description='efficient algorithm for the linear assignment problem',
          long_description=
"""This module is just a simple wrapper for the C++ code written by Jonker
to implement the Jonker-Volgenant algorithm, LAPJV, for the linear
assignment problem.""",
          author='Roy Jonker',
          maintainer='Harold Cooper',
          maintainer_email='hrldcpr@gmail.com')
