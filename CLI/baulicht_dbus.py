import dbus


class BaulichtDbus(object):

    def __init__(self, namespace="de.naptower.Baulicht", path="/"):
        self._bus = dbus.SessionBus()
        self._namespace = namespace
        self._path = path
        self._root_object = self._bus.get_object(self._namespace, self._path)

    def __str__(self):
        return "Baulicht Dbus at %s" % (self._namespace)

    def _get_text_path(self, text):
        if isinstance(text, BaulichText):
            path = text._path
        elif isinstance(text, str):
            path = text
        elif isinstance(text, int):
            path = "/text/%d" % (text)
        else:
            raise TypeError("text must be an object of one of these classes: BaulichtText, int or str")

        return path

    def add_text(self, message):
        return self._root_object.addText(message, -1)

    def list_text(self):
        texts = list()
        for text_paths in self._root_object.texts():
            texts.append(BaulichText(path=text_paths, namespace=self._namespace))

        return texts

    def get_text(self, text):
        return BaulichText(session_bus=self._bus, path=self._get_text_path(text), namespace=self._namespace)

    def remove_text(self, text):
        self._root_object.removeText(self._get_text_path(text))

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


class BaulichSettings(object):
    def __init__(self, path="/settings", namespace="de.naptower.Baulicht"):
        self._bus = dbus.SessionBus()
        self._path = path
        self._namespace = namespace
        self._settings_object = self._bus.get_object(self._namespace, self._path)

    @property
    def dit(self):
        return self._settings_object.dit()

    @dit.setter
    def dit(self, value):
        self._settings_object.setDit(value)

    @property
    def text_spacing(self):
        return self._settings_object.textSpacing()

    @text_spacing.setter
    def text_spacing(self, value):
        self._settings_object.setTextSpacing(value)


class BaulichText(object):

    def __init__(self, path, namespace="de.naptower.Baulicht"):
        self._bus =  dbus.SessionBus()
        self._path = path
        self._namespace = namespace
        self._text_object = self._bus.get_object(self._namespace, self._path)

    def __str__(self):
        return "[%s] %s" % (self._path, self.text())

    @property
    def text(self):
        return self._text_object.text()

    @property
    def repeat(self):
        return self._text_object.repeat()

    @property
    def created(self):
        return self._text_object.creationTimestamp()
