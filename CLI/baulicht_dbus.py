import dbus


class BaulichtDbus(object):

    def __init__(self, namespace="de.naptower.Baulicht"):
        self._namespace = namespace
        self._bus = dbus.SessionBus()
        self._root_object = self._bus.get_object(self._namespace, "/")

    def __str__(self):
        return "Baulicht Dbus at %s" % (self._namespace)

    def add_text(self, message):
        self._root_object.addText(message, 1, 1)

    def list_text(self):
        texts = list()
        for text_paths in self._root_object.texts():
            texts.append(BaulichText(session_bus=self._bus, path=text_paths, namespace=self._namespace))

        return texts

    def get_text(self, text):
        if isinstance(text, BaulichText):
            path = text._path
        elif isinstance(text, str):
            path = text
        elif isinstance(text, int):
            path = "/text/%d" % (text)

        return BaulichText(session_bus=self._bus, path=path, namespace=self._namespace)

    def remove_text(self, text):
        if isinstance(text, BaulichText):
            path = text._path
        elif isinstance(text, str):
            path = text
        elif isinstance(text, int):
            path = "/text/%d" % (text)

        self._root_object.removeText(path)

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

    def __init__(self, session_bus, path, namespace="de.naptower.Baulicht"):
        self._path = path
        self._namespace = namespace
        self._bus = session_bus
        self._text_object = self._bus.get_object(self._namespace, self._path)

    def __str__(self):
        return "[%s] %s" % (self._path, self.text())

    def text(self):
        return self._text_object.text()

    def repeat(self):
        return self._text_object.repeat()
