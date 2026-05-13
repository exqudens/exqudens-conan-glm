# exqudens-conan-glm

## how-to-create-github-conan-package

1. `cmake -P cmake/util.cmake -- conan_create_github_package URL https://github.com/g-truc/glm/archive/refs/tags/1.0.3.zip EXPECTED_MD5 62a0d49dc9db445f077e952e34f13ad2 CHECK_FILE readme.md NAME github-glm VERSION 1.0.3 USER exqudens CHANNEL development`
1. *(optional)* check `conan list 'github-glm/1.0.3:*'`
1. *(optional)* check ``conan cache path 'github-glm/1.0.3:${conan list-output-packages[0]}'``
1. *(optional)* check ``ls -1a ${conan-cache-path-output}``
1. *(optional)* `conan upload github-glm/1.0.3 --remote gitlab`

## list-presets

1. `git clean -xdf`
1. `cmake --list-presets`

## list-ctests

1. `git clean -xdf`
1. `cmake --preset ${preset}`
1. `cmake --build --preset ${preset} --target cmake-test-list`

## vscode

extensions:

- [Command Variable](https://marketplace.visualstudio.com/items?itemName=rioj7.command-variable#pickstringremember) `version >= v1.69.0`

steps:

1. `git clean -xdf`
1. `cmake --preset ${preset}`
1. `cmake --build --preset ${preset} --target vscode`

## clion

1. `git clean -xdf`
1. `cmake --preset ${preset}`
1. `cmake --build --preset ${preset} --target clion`

## build-all-presets

1. `git clean -xdf`
1. `cmake --list-presets | cut -d ':' -f2 | xargs -I '{}' echo '{}' | xargs -I '{}' bash -c "cmake --preset {} || exit 255"`
1. `cmake --list-presets | cut -d ':' -f2 | xargs -I '{}' echo '{}' | xargs -I '{}' bash -c "cmake --build --preset {} || exit 255"`

## build-test-all-presets

1. `git clean -xdf`
1. `cmake --list-presets | cut -d ':' -f2 | xargs -I '{}' echo '{}' | xargs -I '{}' bash -c "cmake --preset {} || exit 255"`
1. `cmake --list-presets | cut -d ':' -f2 | xargs -I '{}' echo '{}' | xargs -I '{}' bash -c "cmake --build --preset {} --target test-app || exit 255"`

## test-all-presets

1. `git clean -xdf`
1. `cmake --list-presets | cut -d ':' -f2 | xargs -I '{}' echo '{}' | xargs -I '{}' bash -c "cmake --preset {} || exit 255"`
1. `cmake --list-presets | cut -d ':' -f2 | xargs -I '{}' echo '{}' | xargs -I '{}' bash -c "cmake --build --preset {} --target cmake-test || exit 255"`

## install-all-presets

1. `git clean -xdf`
1. `cmake --list-presets | cut -d ':' -f2 | xargs -I '{}' echo '{}' | xargs -I '{}' bash -c "cmake --preset {} || exit 255"`
1. `cmake --list-presets | cut -d ':' -f2 | xargs -I '{}' echo '{}' | xargs -I '{}' bash -c "cmake --build --preset {} --target cmake-install || exit 255"`

## export-all-presets

1. `git clean -xdf`
1. `conan list "glm/*"`
1. `conan remove -c "glm"`
1. `cmake --list-presets | cut -d ':' -f2 | xargs -I '{}' echo '{}' | xargs -I '{}' bash -c "cmake --preset {} || exit 255"`
1. `cmake --list-presets | cut -d ':' -f2 | xargs -I '{}' echo '{}' | xargs -I '{}' bash -c "cmake --build --preset {} --target conan-export || exit 255"`
