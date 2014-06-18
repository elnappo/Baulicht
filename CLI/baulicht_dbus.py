import dbus


class BaulichtDbus(object):

    def __init__(self, namespace="de.naptower.Baulicht"):
        self._bus = dbus.SessionBus()
        self._root_object = self._bus.get_object(namespace, "/")

    def add_text(self, message):
        return self._root_object.addText(message, 1, 1)

    def list_text(self):
        texts = list()
        for text in self._root_object.texts():
            texts.append(BaulichText(path=text))

        return texts

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


class BaulichText(object):

    def __init__(self, path, namespace="de.naptower.Baulicht"):
        self._path = path
        self._namespace = namespace
        self._bus = dbus.SessionBus()
        self._text_object = self._bus.get_object(self._namespace, self._path)

    def __str__(self):
        return self._path, self._text_object.text()

    def text(self):
        return self._text_object.text()
