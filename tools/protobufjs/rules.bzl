"""
Rules to interact with protobufjs-cli (`npx pbjs` and `npx pbts`)

Not fully integrated with bazel since react on bazel using the aspectjs doesn't work on windows.
"""

def _protobufjs_library_impl(ctx):
    srcs = ctx.files.srcs
    inputs = depset(srcs)
    output_file = ctx.actions.declare_file(ctx.label.name + ".js")
    outputs = [output_file]

    args = ctx.actions.args()
    args.add("-t", "static_module")
    args.add("-w", "es6")
    args.add("-o", output_file)

    ctx.actions.run(
        mnemonic = "pbjsCompiler",
        executable = ctx.executable._pbjs,
        arguments = [args],
        inputs = inputs,
        outputs = outputs,
    )

    return [DefaultInfo(files = depset(outputs))]

protobufjs_library = rule(
    implementation = _protobufjs_library_impl,
    attrs = {
        "srcs": attr.label_list(allow_files=True, doc=""".proto files to generate js library for"""),
        "_pbjs": attr.label(allow_files=True, default=Label("//:pbjs"), executable=True, cfg="exec", doc="""protobufjs-cli pbjs binary"""),
        "_pbts": attr.label(allow_files=True, default=Label("//:pbts"), executable=True, cfg="exec", doc="""protobufjs-cli pbts binary"""),
    },
)