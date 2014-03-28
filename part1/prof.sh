#!/bin/bash
###############################################################################
# For Coursework 1 F21DP
###############################################################################
# PROF.sh will execute all presented files with iterations in order to
# generate the profiling information for gprof. Once this is done, the
# gprof executable is given the results to generate its profile, which
# is saved into to a seperate directory.
#
# A further process is the generation of valgrind/cachegrind files.
#
# Created by Hans-Nikolai Viessmann
###############################################################################

spinner()
{
    local pid=$1
    local delay=0.75
    local spinstr='|/-\'
    while [ "$(ps a | awk '{print $1}' | grep $pid)" ]; do
        local temp=${spinstr#?}
        printf " [%c]  " "$spinstr"
        local spinstr=$temp${spinstr%"$temp"}
        sleep $delay
        printf "\b\b\b\b\b\b"
    done
    printf "    \b\b\b\b"
}

if [ ! -n "${1}" ]; then
    echo "Missing main argument" >&2
    echo "Usage: ${0} binary [[\"options\"] num_times_each]" >&2
    exit 1
fi
APP=${1}
OPTS=${2:-"15000 30000 100000"}
TIMS=${3:-1}
DIR="${PWD}/${APP}-prof"
RUN="${DIR}/${APP}.log"
ERR="${DIR}/${APP}.err"

[ -d "${DIR}" ] || mkdir ${DIR}
if [ ! -x "${APP}.gprof" ]; then
    echo "Please compile ${APP}.gprof"
    exit 100
elif [ ! -x "${APP}.cache" ]; then
    echo "Please compile ${APP}.cache"
    exit 101
fi

echo "Runtime and Profiling for ${APP} by [${OPTS}]" | tee "${RUN}"
echo "This could take a very long time, have a coffee or watch a movie..."
for i in ${OPTS}; do
    for x in $(seq 1 ${TIMS}); do 
        gprof="${DIR}/${i}.${x}-gprof"
        cache="${DIR}/${i}.${x}-cache"
        echo "${i} times, repeated ${x}:" >> "${RUN}"
        ./"${APP}.gprof" 1 ${i} >> "${RUN}" & 
        echo -n "Getting runtime for ${i}, iter ${x} "
        spinner $!
        echo "DONE"
        
        gprof "${APP}.gprof" > "${gprof}" 2> "${ERR}" &
        echo -n "Anaylising GPROF, iter ${x} "
        spinner $!
        echo "DONE"

        valgrind --tool=cachegrind --quiet \
            --cachegrind-out-file="${cache}" \
            ./"${APP}.cache" 1 ${i} > /dev/null 2> "${ERR}" &
        echo -n "Running Cachegrind, iter ${x} "
        spinner $!
        echo "DONE"
    done
done

