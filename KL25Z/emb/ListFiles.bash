ls -lart `find ./Sources/ -type f -not -name "*~" ` | awk '{code="\\code{."$9"}"; print code}' | sort | xclip -sel clip
