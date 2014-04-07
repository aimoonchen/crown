﻿using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace crown_tests.tests
{
  [JsonObject(MemberSerialization.OptIn)]
  public class TestCategory
  {
    [JsonProperty]
    public String Name;
    [JsonProperty]
    public String Description;
    [JsonProperty]
    public List<Test> Tests;

    public TestCategory(String name, String description)
    {
      Tests = new List<Test>();
      Name = name;
      Description = description;
    }

  }
}
