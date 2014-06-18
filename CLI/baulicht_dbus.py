import dbus


class BaulichtDbus(object):

    def __init__(self, namespace="de.naptower.Baulicht"):
        self._bus = dbus.SessionBus()
        self._root_object = self._bus.get_object(namespace, "/")

    def add_text(self, message):
        return self._root_object.addText(message, 1, 1)

    def list_text(self):
        return list()

    def stop(self):
        self._root_object.stop()

    def start(self):
        self._root_object.start()

    @property
    def paused(self):
        return bool(self._root_object.paused())

    @paused.setter
    def paused(self, value):
        if isinstance(value, bool):
            bool_value = value
        elif isinstance(value, str):
            if value == "on":
                bool_value = True
            elif value == "off":
                bool_value = False
        else:
            raise ValueError

        self._root_object.setPaused(bool_value)

    @property
    def speed(self):
        return self._root_object.speed()

    @speed.setter
    def speed(self, value):
        self._root_object.setSpeed(value)

    @property
    def mode(self):
        if self._root_object.mode() == 0:
            return "text"
        elif self._root_object.mode() == 1:
            return "blink"

    @mode.setter
    def mode(self, value):
        if value == "blink":
            int_value = 1
        elif value == "text":
            int_value = 0
        else:
            raise ValueError('Only "text or "blink are allowd!')

        self._root_object.mode(int_value)
