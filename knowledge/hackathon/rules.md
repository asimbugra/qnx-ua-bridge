# QNX Global Hackathon - official rules & dates

Extracted from the Official Rules page on 2026-11-13.
Source: https://qnx.devpost.com/rules (full text verified; previously 403, captured cleanly this time)

## Key dates

- Registration & submission period: **Nov 2, 2026 11:00 ET - Dec 15, 2026 14:00 ET**
- Judging: Jan 15 - Jan 29, 2027
- Public community voting: Jan 15 - Jan 29, 2027
- Winners announced: on or around Feb 4, 2027
- Sponsor: BlackBerry Ltd; Administrator: Devpost

## Dates that matter for this repo

- Repo was created 2026-11-13, inside the submission period. Good.
- Draft submissions can be saved on Devpost before the deadline; after the deadline
  NO changes are allowed (only Sponsor-permitted IP/PII fixes).

## Eligibility notes

- 18+; Turkey is not on the excluded list (excluded: Brazil, Russia, Crimea, Cuba,
  Iran, North Korea + comprehensively sanctioned regions).
- Individuals, teams and organizations can enter. One person may submit multiple,
  substantially different entries.

## Project requirements (verbatim essentials)

A project must be either:
1. an application, driver, library or component that runs on QNX 8.0 on any supported
   hardware (QEMU included), or
2. a host tool (Windows/macOS/Linux) that builds/tests/analyzes/supports software
   targeting QNX 8.0.

One category must be selected:
- Robotics & Medical (real-time, timing/safety/reliability critical)
- Automotive & Mobility
- Low-level Software (DDK / drivers)
- Developer Tooling & Host Tools
- Open-Source Contribution & Ports

## Submission checklist (hard requirements)

- [ ] Public repo URL on GitHub/GitLab/Bitbucket with all source, assets, instructions
- [ ] Open-source license file, detectable and visible in the repo About section
- [ ] Repo must show the project GENUINELY BUILDS/RUNS for QNX 8.0 (naming QNX in
      README is explicitly called out as insufficient)
- [ ] Exactly one category selected
- [ ] Build & run instructions stating QNX version, target (HW or QEMU), toolchain
- [ ] Text description of features & functionality
- [ ] Demo video < 3 minutes, public on YouTube, showing the project functioning on
      the device it was built for; no third-party trademarks or copyrighted material
      (Siemens logos, licensed music)
- [ ] Evidence of QNX use: identify the relevant files, functions, outputs or
      demonstrations IN THE SUBMISSION DESCRIPTION so reviewers can verify
- [ ] All submission materials in English
- [ ] Original work solely owned by the entrant; third-party SDKs/APIs used per their
      terms; open-source use OK if licenses are respected

## New & existing projects rule

Projects must be newly created between Nov 2 and Dec 15, 2026, OR significantly
updated after Nov 2 with an explanation. (This repo: newly created - clean case.)

## Open-Source Contribution & Ports category specifics (not our category)

Requires a NEW repo created during the submission period with the porting layer,
QNX build files, instructions; upstream referenced by URL; NO fork of upstream.
Our repo follows the same hygiene anyway (open62541 fetched as a pinned dependency).

## Prizes (summary)

- Grand Prize $10,000 + podcast + coffee chat with QNX CEO
- Best of each category $4,000 (+ runner-up $2,000 each; 5 categories)
- Honorable mentions 3x $1,000
- Bonus: Best Codelab/Tutorial $3,500; Best use of QNX-specific Technologies $3,500
- Community Choice: blog/social feature + swag
- A project can win max: 1 Overall + 1 Bonus + 1 Community Choice

## Judging (section 6)

Two stages: Stage 1 pass/fail viability (fits theme, uses required platform).
Stage 2: four EQUALLY WEIGHTED criteria - see judging.md.
Tie-break: highest score in the first criterion (Technological Implementation), then
next, then judge vote.
