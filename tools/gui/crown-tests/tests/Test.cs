﻿using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace crown_tests.tests
{
  [JsonObject(MemberSerialization.OptIn)]
  public class Test
  {
    [JsonProperty]
    public String Name;
    [JsonProperty]
    public String Description;
  }
}
