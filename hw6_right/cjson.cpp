#include <iostream>
#include <string>

#include "/usr/include/python3.11/Python.h"
PyObject* json_dumps(PyObject* self, PyObject* args) {
  PyObject* dict;

  if (!PyArg_ParseTuple(args, "O!", &PyDict_Type, &dict)) {
    printf("ERROR: Failed to set item\n");
    return NULL;
  }

  PyObject* items = PyDict_Items(dict);
  int size = PyDict_Size(dict);
  std::string res = "{";
  double temp;
  for (Py_ssize_t i = 0; i < size; ++i) {
    PyObject* item = PyList_GetItem(items, i);
    PyObject* key = PyTuple_GetItem(item, 0);
    PyObject* value = PyTuple_GetItem(item, 1);
    res += "\"";
    res += PyUnicode_AsUTF8(key);
    res += "\"";
    res += ":";
    if (PyLong_Check(value)) {
      temp = PyLong_AsLong(value);
      res += std::to_string((int)temp);
    } else if (PyFloat_Check(value)) {
      temp = PyFloat_AsDouble(value);
      std::string tempBuf = std::to_string(temp);
      for (int i = tempBuf.size() - 1; tempBuf[i] == '0'; i--) {
        tempBuf.erase(tempBuf.size() - 1, 1);
      }

      res += tempBuf;
    } else {
      res += "\"";
      res += (PyUnicode_AsUTF8(value));
      res += "\"";
    }
    if (i != size - 1) {
      res += ",";
    }
  }
  res += "}";
  char* res_type = &res[0];
  return Py_BuildValue("s", res_type);
}

PyObject* json_loads(PyObject* self, PyObject* args) {
  Py_Initialize();
  PyObject* string;
  std::string toWork;
  if (!PyArg_ParseTuple(args, "O", &string)) {
    printf("ERROR: Failed to set item\n");
    return NULL;
  }
  toWork = PyUnicode_AsUTF8(string);
  PyObject* dict = PyDict_New();
  std::string tempKey;
  std::string tempValue;
  char* keyObj;
  char* valueObj;
  for (int i = 0; i < toWork.size(); i++) {
    if (toWork[i] != ':') {
      if (toWork[i] != '\"' && toWork[i] != '{') {
        tempKey += toWork[i];
      }
    } else {
      if (toWork[i + 1] == ' ') {
        i += 2;
      } else {
        i += 1;
      }
      bool flagIfDigit = true;
      bool flagIfHadDot = false;
      while (toWork[i] != ',') {
        if (toWork[i] != '\"' && toWork[i] != '}') {
          tempValue += toWork[i];
        }
        i++;
        if (i == toWork.size()) {
          break;
        }
      }
      int counter = 0;
      for (int j = 0; j < tempValue.size(); j++) {
        if (!std::isdigit(tempValue[j])) {
          flagIfDigit = true;
          if (tempValue[j] == '.') {
            flagIfHadDot = true;
            counter += 1;
            if (counter == 2) {
              flagIfHadDot = false;
              counter = 0;
              break;
            }
          } else if (tempValue[j] == '-') {
            continue;
          } else {
            flagIfDigit = false;
            flagIfHadDot = false;
            break;
          }
        }
      }
      keyObj = &tempKey[0];

      if (flagIfDigit && flagIfHadDot) {
        PyDict_SetItem(dict, Py_BuildValue("s", keyObj),
                       Py_BuildValue("d", std::stod(tempValue)));
      }
      if (flagIfDigit && !flagIfHadDot) {
        PyDict_SetItem(dict, Py_BuildValue("s", keyObj),
                       Py_BuildValue("i", std::stoi(tempValue)));
      }
      if (!flagIfDigit && !flagIfHadDot) {
        valueObj = &tempValue[0];
        PyDict_SetItem(dict, Py_BuildValue("s", keyObj),
                       Py_BuildValue("s", valueObj));
      }
      tempKey = "";
      tempValue = "";
      i++;
    }
  }
  return dict;
}

static PyMethodDef module_funcs[] = {
    {"dumps", json_dumps, METH_VARARGS, "homework6"},
    {"loads", json_loads, METH_VARARGS, "homework6"},
    {NULL, NULL, 0, NULL},
};

static PyModuleDef module = {PyModuleDef_HEAD_INIT, "cjson", "Model cool", -1,
                             module_funcs};

PyMODINIT_FUNC PyInit_cjson() { return PyModule_Create(&module); }