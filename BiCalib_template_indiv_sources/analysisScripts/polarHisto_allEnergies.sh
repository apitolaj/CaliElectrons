#!/bin/bash
#SBATCH --job-name=polarHisto_allEnergies
#SBATCH --mem=1G
#SBATCH --licenses=sps
#SBATCH --time=00:10:00
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=1

PROFILE_SCRIPT="${THRONG_DIR}/config/supernemo_profile.bash"
STACK_NAME="falaise@2026-04-07"

set +e
set +u
source "${PROFILE_SCRIPT}"
PROFILE_RC=$?
snswmgr_load_stack "${STACK_NAME}"
STACK_RC=$?
set -e
set -u

for i in $(seq 0 5);
do
    for k in $(seq 0 6);
    do
    	
        DST_DIR="ANALYSIS/Source_${i}_${k}"
        
        if [ -d ${DST_DIR} ]; then
        
        sed "s|SOURCE_PLACEHOLDER|${i}_${k}|g; s|ENERGY_PLACEHOLDER1|allEnergies|g; s|ENERGY_PLACEHOLDER2|all energies|g" "polarHisto_plotAngles.cpp" > "${DST_DIR}/polarHisto_plotAngles_Source_${i}_${k}.cpp"
        
	(cd ${DST_DIR} && root -q -l -b 'polarHisto_plotAngles_Source_'${i}_${k}'.cpp("angles_envelope_allEnergies_Source_'${i}_${k}'.root","angles_noEnvelope_allEnergies_Source_'${i}_${k}'.root")')
	
	fi
	
    done
done
