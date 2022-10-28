from requests import get
from os.path import join as pjoin, exists as p_exists
from os import makedirs as mkdir
from os import listdir as ls
from os import remove as rm_
from os.path import isdir, isfile
from os import environ
from github import Github
from alive_progress import alive_bar
import shutil
import platform
from subprocess import run
from zipfile import ZipFile
import textwrap
from sys import exit

# from gh_token import GITHUB_TOKEN

base_url = "https://pyscript.net/latest/"
base_name = "pyscript"
extentions = (".py", ".css", ".js", ".js.map")

pyodide_repo_name = "pyodide/pyodide"

if isfile(".env"):
    environ.update(
        {
            k: v
            for k, v in [line.split("=") for line in open(".env").read().splitlines()]
        }
    )


if environ.get("GITHUB_TOKEN"):
    g = Github(environ["GITHUB_TOKEN"])

elif "GITHUB_TOKEN" in dir():
    g = Github(GITHUB_TOKEN)

else:
    print(
        "No GITHUB_TOKEN found in .env file or environment\n"
        "You can get one from:\n"
        "https://docs.github.com/en/authentication/keeping-your-account-and-data-secure/creating-a-personal-access-token\n"
    )
    try:
        g = Github(input("Please enter your github token: "))
    except KeyboardInterrupt:
        print("\nCanceled by user")
        exit(1)


platforms = {
    "linux": "linux",
    "win32": "win",
    "darwin": "mac",
}
current_ = platforms[platform.system().lower()]


def rm(path: str) -> None:
    if isdir(path):
        shutil.rmtree(path, ignore_errors=True)
    else:
        rm_(path)


def get_pyodide_info():
    repo = g.get_repo(pyodide_repo_name)
    release = repo.get_latest_release()
    releases = release.get_assets().get_page(page=0)
    for release_ in releases:
        if (
            release_.name.endswith(".bz2")
            and release_.name.startswith("pyodide")
            and not "core"
            in release_.name  # we don' want the core, we want the full package
        ):

            return {
                "filename": release_.name,
                "url": release_.browser_download_url,
                "size": release_.size,
                "version": release.tag_name,
            }
    # Amen


def download_file(
    url: str, filename: str, size: int = 0, chunk_size: int = 1024
) -> None:
    stream = get(url, stream=True)
    if size == 0:
        size = int(stream.headers.get("content-length", 0))

    with open(filename, "wb") as f:
        with alive_bar(
            size // chunk_size,
            # bar="blocks",
            # Dony
        ) as bar:
            for chunk in stream.iter_content(chunk_size=chunk_size):
                f.write(chunk)
                bar()


def add_to_path(path: str) -> None:
    if path not in environ["PATH"]:
        environ["PATH"] += f";{path}"


if __name__ == "__main__":
    chunk_size = 1024
    if p_exists("pyscript"):
        rm("pyscript")
    mkdir("PyScript")
    print("Downloading PyScript files...")
    for ext in extentions:
        download_file(
            base_url + base_name + ext,
            pjoin("PyScript", base_name + ext),
        )
    pyodide_info = get_pyodide_info()
    print("Downloading Pyodide {}...".format(pyodide_info["version"]))
    download_file(
        pyodide_info["url"],
        pjoin(pyodide_info["filename"]),
        pyodide_info["size"],
    )
    print("Extracting Pyodide...")
    current_filename = pyodide_info["filename"]
    print("Downloading 7zip...")
    download_file(
        "https://www.dropbox.com/s/bvbw818ecoobmgp/7z.zip?dl=1",
        "7z.zip",
    )
    with ZipFile("7z.zip", "r") as zipObj:
        zipObj.extractall()

    add_to_path(current_)
    # 7z x foo.tar.bz2
    run(f"7z x -bb3 -y {current_filename}", shell=True)
    current_filename = current_filename.removesuffix(".bz2")
    # 7z x foo.tar
    run(f"7z x -bb3 -y {current_filename}", shell=True)

    pyo = "pyodide"
    for file in ls(pyo):
        shutil.move(pjoin(pyo, file), base_name)
    rm(pyo)
    rm(current_filename)
    rm(pyodide_info["filename"])
    rm("7z.zip")
    rm("7z")
    print("Done, PyScript is ready for local use!")
    print("You can use pyscript in html files like this:")
    print()

    # Colorize the code (using pygments)
    code = textwrap.dedent(
        f"""
    <link rel="stylesheet" href="{base_name}/pyscript.css"/>
    <script defer src="{base_name}/pyscript.js"></script>
    <py-config>
    - autoclose_loader: true
    - runtimes:
      -
        src: "{base_name}/pyodide.js"
        name: pyodide-{pyodide_info["version"]}
        lang: python
    </py-config>
    """
    )
    print(code)
    print()
    input("Cya 👋🏻 [PRESS ENTER TO EXIT]")
    exit(0)
