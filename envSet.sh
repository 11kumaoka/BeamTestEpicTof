source /opt/detector/epic-main/bin/thisepic.sh
export PREFIX=${PWD}/install
export JANA_PLUGIN_PATH=${PREFIX}/lib:${JANA_PLUGIN_PATH}
export LD_LIBRARY_PATH=${PREFIX}/lib:${LD_LIBRARY_PATH}
export DD4HEP_LIBRARY_PATH=${PREFIX}/lib:${DD4HEP_LIBRARY_PATH}
export CPATH=${PREFIX}/include:/opt/local/include/EICrecon:${CPATH}
rm -rf build install
mkdir build install output
