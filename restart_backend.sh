# restart_backend.sh
# Runs at 4:50 UTC
# Stop C++ gracefully (i.e. first stop consuming records from PHP and timed tasks from database) and restart

cd /repo/SOLAS-Match-Backend
touch /repo/SOLAS-Match-Backend/STOP_consumeFromQueue
sleep 60
kill `ps -ef | grep PluginHandler | grep -v grep | grep -Eo '[0-9]+' | head --lines 1`
rm /repo/SOLAS-Match-Backend/STOP_consumeFromQueue
./run_daemon.sh &disown
