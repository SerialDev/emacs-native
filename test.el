;; Load rs module to allow hot reloading
(load  (concat (file-name-directory buffer-file-name) "rs-module/target/debug/libemacs_rs_module.so"))

;; Load rs modules
;; (rs-module/load  (concat (file-name-directory buffer-file-name) "greet/target/debug/libgreet.so"))
(rs-module/load  "/mnt/emacs-bankrupt/native-plugins/rs-greet/target/debug/libgreet.so")

;; Load c modules
(load  (concat (file-name-directory buffer-file-name) "c-plugin/build/libparser1.so"))


(greeting-say-hello "pandas")

