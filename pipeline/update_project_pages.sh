#! /bin/sh
set -e

if [ ! $# -eq 2 ]; then
    echo "Called with the a wrong number of arguments, expected 2 got $#"
    echo "$@"
    exit 1
fi

REPOSITORY=$(echo "${1}" | tr  '[:upper:]' '[:lower:]' )
REPO_OWNER=$(echo "${REPOSITORY}" | cut -f1 -d/ )
REPO_NAME=$(echo "${REPOSITORY}" | cut -f2 -d/ )
PAGES_URL="https://${REPO_OWNER}.github.io/${REPO_NAME}/"

echo "Update project pages variables:"
echo "REPOSITORY = ${REPOSITORY}"
echo "REPO_OWNER = ${REPO_OWNER}"
echo "REPO_NAME = ${REPO_NAME}"
echo "PAGES_URL = ${PAGES_URL}"


if [ ! $(grep -q "${PAGES_URL}" README.md) ]; then
    echo "*** Error: The url/link that should point to the GitHub pages for"
    echo "***        the repository should be set to ${PAGES_URL} but is set to"
    echo "***        something else. Fix the link and try again."
    exit 1
fi

# Update firmware.zip
rm -f proj_pages/firmware/firmware.zip
zip proj_pages/firmware/firmware.zip firmware.*

# Update test_result.xml
cp -f test_result.xml proj_pages/testdata/test_result.xml

# Update date stamps
NOW=$(date)
sed "s/TTTTTTTTTTTTTT/${NOW}/g" < proj_pages/index.html.template > index_tmp.html
sed "s/RRRRRRRRRRRRRR/${REPOSITORY}/g" < index_tmp.html > index.html
mv -f index.html proj_pages/index.html

exit 0
