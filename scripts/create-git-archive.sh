#!/bin/bash
set -e

url=`git remote get-url origin`
project=`basename "$url"`
project="${project%.git}"
version="`git describe --abbrev=0``git log -n 1 --pretty=format:"+%cd~git%h" --date=format:%Y%m%d master`"
version="${version#v}"

git-archive-all --verbose --prefix "$project-$version/" "$project-$version.tar"
zopfli "$project-$version.tar"
rm -f "$project-$version.tar"
