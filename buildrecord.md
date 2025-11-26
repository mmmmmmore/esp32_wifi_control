
/Users/maochun/esp32prj/Project_CAM/branch/esp32_wifi_control/handler/ota_handler/ota_handler.c: In function 'ota_start':
/Users/maochun/esp32prj/Project_CAM/branch/esp32_wifi_control/handler/ota_handler/ota_handler.c:98:10: error: 'esp_https_ota_config_t' has no member named 'cert_pem'
   98 |         .cert_pem = NULL,   // 如果有 HTTPS 证书，可以在这里配置
      |          ^~~~~~~~
/Users/maochun/esp32prj/Project_CAM/branch/esp32_wifi_control/handler/ota_handler/ota_handler.c:99:10: error: 'esp_https_ota_config_t' has no member named 'partial_http_download'
   99 |         .partial_http_download = false,
      |          ^~~~~~~~~~~~~~~~~~~~~
[5/14] cd /Users/maochun/esp32prj/Project_CAM/branch/es...eta-len=4 --follow-symlinks --use-magic --use-magic-len
ninja: build stopped: subcommand failed.



maochun@MMMBP ~ % brew install node
✔︎ JSON API cask.jws.json                                                                                                           [Downloaded   15.0MB/ 15.0MB]
✔︎ JSON API formula.jws.json                                                                                                        [Downloaded   31.7MB/ 31.7MB]
Warning: You are using macOS 12.
We (and Apple) do not provide support for this old version.
You may have better luck with MacPorts which supports older versions of macOS:
  https://www.macports.org

This is a Tier 3 configuration:
  https://docs.brew.sh/Support-Tiers#tier-3
You can report Tier 3 unrelated issues to Homebrew/* repositories!
Read the above document before opening any issues or PRs.

==> Fetching downloads for: node
✔︎ API Source node.rb                                                                                                               [Verifying    11.9KB/ 11.9KB]
✔︎ Resource node--npm                                                                                                               [Verifying     2.7MB/  2.7MB]
✔︎ Formula node (25.2.1)                                                                                                            [Verifying    53.3MB/ 53.3MB]
==> Installing dependencies for node: z3, ninja, pcre2, swig and llvm
==> Installing node dependency: z3
==> Downloading https://raw.githubusercontent.com/Homebrew/homebrew-core/f7b11851b077fabca6c7996ca223de41edbcb57d/Formula/z/z3.rb
######################################################################################################################################################### 100.0%
Error: An exception occurred within a child process:
  FormulaUnavailableError: No available formula with the name "formula.jws.json".
maochun@MMMBP ~ % brew update
==> Updating Homebrew...
Already up-to-date.
maochun@MMMBP ~ % 


maochun@MMMBP ~ % brew install node
✔︎ JSON API cask.jws.json                                                                                                           [Downloaded   15.0MB/ 15.0MB]
✔︎ JSON API formula.jws.json                                                                                                        [Downloaded   31.7MB/ 31.7MB]
Warning: You are using macOS 12.
We (and Apple) do not provide support for this old version.
You may have better luck with MacPorts which supports older versions of macOS:
  https://www.macports.org

This is a Tier 3 configuration:
  https://docs.brew.sh/Support-Tiers#tier-3
You can report Tier 3 unrelated issues to Homebrew/* repositories!
Read the above document before opening any issues or PRs.

==> Fetching downloads for: node
✔︎ API Source node.rb                                                                                                               [Verifying    11.9KB/ 11.9KB]
✔︎ Resource node--npm                                                                                                               [Verifying     2.7MB/  2.7MB]
✔︎ Formula node (25.2.1)                                                                                                            [Verifying    53.3MB/ 53.3MB]
==> Installing dependencies for node: z3, ninja, pcre2, swig and llvm
==> Installing node dependency: z3
==> Downloading https://raw.githubusercontent.com/Homebrew/homebrew-core/f7b11851b077fabca6c7996ca223de41edbcb57d/Formula/z/z3.rb
######################################################################################################################################################### 100.0%
Error: An exception occurred within a child process:
  FormulaUnavailableError: No available formula with the name "formula.jws.json".
maochun@MMMBP ~ % brew update
==> Updating Homebrew...
Already up-to-date.
maochun@MMMBP ~ % 





/Users/maochun/esp32prj/Project_CAM/branch/esp32_wifi_control/handler/ota_handler/ota_handler.c: In function 'ota_start':
/Users/maochun/esp32prj/Project_CAM/branch/esp32_wifi_control/handler/ota_handler/ota_handler.c:93:35: error: passing argument 1 of 'esp_https_ota' from incompatible pointer type [-Wincompatible-pointer-types]
   93 |     esp_err_t ret = esp_https_ota(&ota_config);
      |                                   ^~~~~~~~~~~
      |                                   |
      |                                   esp_http_client_config_t *
In file included from /Users/maochun/esp32prj/Project_CAM/branch/esp32_wifi_control/handler/ota_handler/ota_handler.c:4:
/Users/maochun/esp32prj/esp-idf/components/esp_https_ota/include/esp_https_ota.h:114:55: note: expected 'const esp_https_ota_config_t *' but argument is of type 'esp_http_client_config_t *'
  114 | esp_err_t esp_https_ota(const esp_https_ota_config_t *ota_config);
      |                         ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^~~~~~~~~~

