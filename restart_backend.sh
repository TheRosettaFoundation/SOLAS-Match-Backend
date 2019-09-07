# restart_backend.sh
# Stop C++ gracefully (i.e. first stop consuming messages from rabbitmq) and restart
# Ideally this should not be done between 7 and 7:20 UTC because main deadline check is just time based

cd /repo/SOLAS-Match-Backend
touch /repo/SOLAS-Match-Backend/STOP_consumeFromQueue
sleep 10
kill `ps -ef | grep PluginHandler | grep -v grep | grep -Eo '[0-9]+' | head --lines 1`
rm /repo/SOLAS-Match-Backend/STOP_consumeFromQueue
./run_daemon.sh &disown
