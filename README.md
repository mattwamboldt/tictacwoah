This Project is a cool new take on Tic Tac Toe.

By default it will use the data directory, but can run off of the archives by
changing a setting in the devoptions.xml file

Here's how the project is organized:

Assets
=====

These are the raw art and audio files, uncompressed. Stuff like psds,
illustrator files, raw sounds and recordings, fonts, databases, that kind of thing.

Be careful with committing revisions here because binary files can make the repo huge.

Data
=====
Where any intermediary files go. Stuff that gets exported from the base
assets, so pngs or tiffs, compressed wavs and ogg files, xml, bitmap fonts, etc.

Stuff in this folder can be read directly by the game during development for
quick testing but make sure to update the source assets as well.

Be careful with submitting revisions here because binary files can make the repo huge.

Source
=====
Where all the source code lives. Including the engine and third party libraries.

Game
=====

Where the release version of the game gets built to. This also has all the archived
files that are built from our data directory, along with settings. This version has
everything compressed and optimized.

Test
=====

Where the debug version of the game gets built to also contains test scripts and debugging capabilities.

Tools
=====
Houses command line tools and editors for game data. Nothing in here yet, but will in the future.

Temp
=====
This is where all temporary files go. Object files, Pdbs, Converted and optimized data before it gets archived.
If you delete this folder it'll force a rebuild.