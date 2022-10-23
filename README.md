# PyScript Local
An app to help in setting up pyscript locally

## How it works

- First things first, it is gonna download `pyscript.js` `pyscript.css` `pyscript.py` and the map files linked to them
- Then it is gonna get information about the latest version of [`pyodide`](https://github.com/pyodide/pyodide) via [`github API`](https://docs.github.com/en/rest)
- Then, download pyodide full
- Download 7zip for file extraction
- Unzip pyodide with 7zip
- Move all the collected files (execpt 7zip) to `PyScript` folder
- delete the unwanted files
