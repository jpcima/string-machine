# Release checklist

- Edit the changelog
- Edit the version in DistrhoPluginInfo
- Push the annotated tag in the form "vX.Y.Z"
- Create the archive with git-archive-all
- Prefix archive contents with "project-X.Y.Z/"
- Compress the archive with zopfli
- Create the Github release
- Update OBS package sources
