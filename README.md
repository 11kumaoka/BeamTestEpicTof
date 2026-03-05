# BeamTestEpicTof
EIC Online Reconstruction for BeamTest

==== How to run ====

run ./eic-shell

source /opt/detector/epic-main/bin/thisepic.sh
cd BeamTestTOF/TofClustering/
export EICrecon_MY=${PWD}/EICrecon_MY
export CPATH="/opt/local/include/EICrecon:$CPATH"
cd build
cmake ..   -DJANA_DIR="$JANA_HOME/lib/cmake/JANA"   -DCMAKE_INSTALL_PREFIX="$EICrecon_MY"
make install -j8

eicrecon -Pplugins=TofCluPlugin  -Ppodio:output_collections="KumaTOFBarrelClusterHits"  -Pdd4hep:xml_files=epic_craterlake_tracking_only.xml ../../../input/output.root  -Pjana:nevents=5

